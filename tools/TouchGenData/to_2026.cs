using System;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.ServiceProcess;
using System.Windows.Forms;

class Program
{
    [StructLayout(LayoutKind.Sequential)]
    struct SYSTEMTIME
    {
        public ushort Year;
        public ushort Month;
        public ushort DayOfWeek;
        public ushort Day;
        public ushort Hour;
        public ushort Minute;
        public ushort Second;
        public ushort Milliseconds;
    }

    [DllImport("kernel32.dll", SetLastError = true)]
    static extern bool SetLocalTime(ref SYSTEMTIME lpSystemTime);

    [STAThread]
    static int Main()
    {
        if (!IsAdministrator())
        {
            try
            {
                Process.Start(new ProcessStartInfo
                {
                    FileName = Process.GetCurrentProcess().MainModule.FileName,
                    UseShellExecute = true,
                    Verb = "runas"
                });
                return 0;
            }
            catch
            {
                ShowNotify("同步最新时间", "需要管理员权限。", true);
                return 1;
            }
        }

        string detail;
        bool ok = TrySyncLatestTime(out detail);
        string nowText = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");

        if (ok)
        {
            ShowNotify("同步最新时间", "已同步到最新时间\n" + nowText, false);
            return 0;
        }

        ShowNotify("同步最新时间", "同步失败\n" + detail, true);
        return 1;
    }

    static bool TrySyncLatestTime(out string detail)
    {
        detail = "";

        try
        {
            using (var sc = new ServiceController("W32Time"))
            {
                try { RunHidden("sc.exe", "config W32Time start= demand"); } catch { }

                sc.Refresh();
                if (sc.Status != ServiceControllerStatus.Running)
                {
                    sc.Start();
                    sc.WaitForStatus(ServiceControllerStatus.Running, TimeSpan.FromSeconds(15));
                }
            }
        }
        catch (Exception ex)
        {
            // continue to HTTP fallback
            detail = "时间服务: " + ex.Message;
        }

        try
        {
            RunHidden("w32tm.exe", "/config /manualpeerlist:\"time.windows.com,0x9 time.nist.gov,0x9\" /syncfromflags:manual /update");
        }
        catch { }

        int exitCode = -1;
        try { exitCode = RunHidden("w32tm.exe", "/resync /force"); } catch { }

        if (exitCode == 0)
        {
            detail = "w32tm";
            return true;
        }

        try
        {
            DateTime? netTime = GetHttpDate("https://www.baidu.com");
            if (netTime == null)
                netTime = GetHttpDate("https://www.microsoft.com");
            if (netTime == null)
                netTime = GetHttpDate("https://www.cloudflare.com");

            if (netTime != null)
            {
                DateTime local = netTime.Value.ToLocalTime();
                if (SetSystemLocalTime(local))
                {
                    detail = "HTTP";
                    return true;
                }
            }

            if (string.IsNullOrEmpty(detail))
                detail = "w32tm 退出码 " + exitCode + "，HTTP 时间源不可用";
            else
                detail = detail + "；w32tm=" + exitCode + "；HTTP 不可用";
            return false;
        }
        catch (Exception ex)
        {
            detail = "同步异常: " + ex.Message;
            return false;
        }
    }

    static DateTime? GetHttpDate(string url)
    {
        var req = (System.Net.HttpWebRequest)System.Net.WebRequest.Create(url);
        req.Method = "HEAD";
        req.Timeout = 8000;
        req.AllowAutoRedirect = true;
        using (var resp = (System.Net.HttpWebResponse)req.GetResponse())
        {
            string dateHeader = resp.Headers["Date"];
            if (string.IsNullOrEmpty(dateHeader)) return null;
            DateTime dt;
            if (DateTime.TryParse(dateHeader, null,
                System.Globalization.DateTimeStyles.AdjustToUniversal, out dt))
            {
                return dt;
            }
        }
        return null;
    }

    static int RunHidden(string fileName, string args)
    {
        var psi = new ProcessStartInfo
        {
            FileName = fileName,
            Arguments = args,
            UseShellExecute = false,
            CreateNoWindow = true,
            RedirectStandardOutput = true,
            RedirectStandardError = true
        };
        using (var p = Process.Start(psi))
        {
            p.WaitForExit(20000);
            return p.ExitCode;
        }
    }

    static bool IsAdministrator()
    {
        using (var identity = WindowsIdentity.GetCurrent())
        {
            return new WindowsPrincipal(identity).IsInRole(WindowsBuiltInRole.Administrator);
        }
    }

    static bool SetSystemLocalTime(DateTime dt)
    {
        SYSTEMTIME st = new SYSTEMTIME
        {
            Year = (ushort)dt.Year,
            Month = (ushort)dt.Month,
            Day = (ushort)dt.Day,
            Hour = (ushort)dt.Hour,
            Minute = (ushort)dt.Minute,
            Second = (ushort)dt.Second,
            Milliseconds = (ushort)dt.Millisecond,
            DayOfWeek = (ushort)dt.DayOfWeek
        };
        return SetLocalTime(ref st);
    }

    static void ShowNotify(string title, string body, bool isError)
    {
        var form = new Form();
        form.FormBorderStyle = FormBorderStyle.None;
        form.StartPosition = FormStartPosition.Manual;
        form.ShowInTaskbar = false;
        form.TopMost = true;
        form.BackColor = Color.FromArgb(32, 32, 32);
        form.Size = new Size(380, 110);

        var screen = Screen.PrimaryScreen.WorkingArea;
        form.Location = new Point(screen.Right - form.Width - 16, screen.Bottom - form.Height - 16);

        var titleLabel = new Label();
        titleLabel.AutoSize = false;
        titleLabel.Location = new Point(16, 14);
        titleLabel.Size = new Size(348, 24);
        titleLabel.ForeColor = Color.White;
        titleLabel.Font = new Font("Microsoft YaHei UI", 11f, FontStyle.Bold);
        titleLabel.Text = title;
        titleLabel.BackColor = Color.Transparent;

        var bodyLabel = new Label();
        bodyLabel.AutoSize = false;
        bodyLabel.Location = new Point(16, 42);
        bodyLabel.Size = new Size(348, 56);
        bodyLabel.ForeColor = Color.FromArgb(220, 220, 220);
        bodyLabel.Font = new Font("Microsoft YaHei UI", 9f, FontStyle.Regular);
        bodyLabel.Text = body;
        bodyLabel.BackColor = Color.Transparent;

        var accent = new Panel();
        accent.Location = new Point(0, 0);
        accent.Size = new Size(4, form.Height);
        accent.BackColor = isError ? Color.FromArgb(232, 17, 35) : Color.FromArgb(16, 124, 16);

        form.Controls.Add(accent);
        form.Controls.Add(titleLabel);
        form.Controls.Add(bodyLabel);

        var timer = new Timer();
        timer.Interval = 3000;
        timer.Tick += (s, e) =>
        {
            timer.Stop();
            form.Close();
        };

        form.Shown += (s, e) => timer.Start();
        form.ShowDialog();
    }
}