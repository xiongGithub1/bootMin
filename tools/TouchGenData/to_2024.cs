using System;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Security.Principal;
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
                ShowNotify("切换到 2024", "需要管理员权限才能修改系统时间。", true);
                return 1;
            }
        }

        DateTime now = DateTime.Now;
        int day = now.Day;
        int lastDay = DateTime.DaysInMonth(2024, now.Month);
        if (day > lastDay) day = lastDay;

        DateTime target = new DateTime(2024, now.Month, day, now.Hour, now.Minute, now.Second, now.Millisecond);
        if (!SetSystemLocalTime(target))
        {
            ShowNotify("切换到 2024", "切换失败，请重试。", true);
            return 1;
        }

        ShowNotify(
            "切换到 2024",
            "已切换到 2024 年（月日时分秒不变）" + Environment.NewLine + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"),
            false);
        return 0;
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
        form.Size = new Size(360, 96);
        form.Padding = new Padding(0);

        var screen = Screen.PrimaryScreen.WorkingArea;
        form.Location = new Point(screen.Right - form.Width - 16, screen.Bottom - form.Height - 16);

        var titleLabel = new Label();
        titleLabel.AutoSize = false;
        titleLabel.Location = new Point(16, 14);
        titleLabel.Size = new Size(328, 24);
        titleLabel.ForeColor = Color.White;
        titleLabel.Font = new Font("Microsoft YaHei UI", 11f, FontStyle.Bold);
        titleLabel.Text = title;
        titleLabel.BackColor = Color.Transparent;

        var bodyLabel = new Label();
        bodyLabel.AutoSize = false;
        bodyLabel.Location = new Point(16, 42);
        bodyLabel.Size = new Size(328, 40);
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

        var timer = new System.Windows.Forms.Timer();
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