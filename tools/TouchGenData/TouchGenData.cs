using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace Last364Tools
{
    internal static class TouchGenData
    {
        [STAThread]
        private static int Main(string[] args)
        {
            string[] filteredArgs = args.Where(a =>
                !string.Equals(a, "--pause", StringComparison.OrdinalIgnoreCase) &&
                !string.Equals(a, "-p", StringComparison.OrdinalIgnoreCase)).ToArray();

            string projectRoot = ResolveProjectRoot(filteredArgs);
            if (projectRoot == null)
            {
                ShowNotify(
                    "更新 GenData 时间戳",
                    "找不到 Appl\\GenData 目录\n请将 exe 放在 last364 工程内运行",
                    true);
                return 1;
            }

            string genDataPath = Path.Combine(projectRoot, "Appl", "GenData");
            DateTime now = DateTime.Now;
            int updated = 0;
            int skipped = 0;

            try
            {
                foreach (string file in Directory.EnumerateFiles(genDataPath, "*.*", SearchOption.AllDirectories))
                {
                    string ext = Path.GetExtension(file);
                    if (!ext.Equals(".c", StringComparison.OrdinalIgnoreCase) &&
                        !ext.Equals(".h", StringComparison.OrdinalIgnoreCase))
                    {
                        continue;
                    }

                    DateTime writeTime = File.GetLastWriteTime(file);
                    if (writeTime.Year == 2024)
                    {
                        File.SetLastWriteTime(file, now);
                        updated++;
                    }
                    else
                    {
                        skipped++;
                    }
                }
            }
            catch (Exception ex)
            {
                ShowNotify(
                    "更新 GenData 时间戳",
                    "更新失败\n" + ex.Message,
                    true);
                return 1;
            }

            if (updated == 0)
            {
                ShowNotify(
                    "更新 GenData 时间戳",
                    "未发现 2024 时间戳的文件\n已跳过 " + skipped + " 个",
                    false);
                return 0;
            }

            ShowNotify(
                "更新 GenData 时间戳",
                "已更新 " + updated + " 个，跳过 " + skipped + " 个\n" + now.ToString("yyyy-MM-dd HH:mm:ss"),
                false);
            return 0;
        }

        private static string ResolveProjectRoot(string[] args)
        {
            List<string> candidates = new List<string>();

            if (args.Length > 0)
            {
                string argPath = Path.GetFullPath(args[0]);
                if (Directory.Exists(argPath))
                {
                    candidates.Add(argPath);
                }
            }

            candidates.Add(Directory.GetCurrentDirectory());

            string exeDir = AppDomain.CurrentDomain.BaseDirectory.TrimEnd(
                Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar);
            candidates.Add(exeDir);

            if (exeDir.IndexOf("tools", StringComparison.OrdinalIgnoreCase) >= 0)
            {
                DirectoryInfo dir = new DirectoryInfo(exeDir);
                for (int i = 0; i < 4 && dir.Parent != null; i++)
                {
                    candidates.Add(dir.Parent.FullName);
                    dir = dir.Parent;
                }
            }

            foreach (string candidate in candidates.Distinct(StringComparer.OrdinalIgnoreCase))
            {
                string genData = Path.Combine(candidate, "Appl", "GenData");
                if (Directory.Exists(genData))
                {
                    return candidate;
                }
            }

            return null;
        }

        private static void ShowNotify(string title, string body, bool isError)
        {
            Form form = new Form();
            form.FormBorderStyle = FormBorderStyle.None;
            form.StartPosition = FormStartPosition.Manual;
            form.ShowInTaskbar = false;
            form.TopMost = true;
            form.BackColor = Color.FromArgb(32, 32, 32);
            form.Size = new Size(380, 110);

            Rectangle screen = Screen.PrimaryScreen.WorkingArea;
            form.Location = new Point(screen.Right - form.Width - 16, screen.Bottom - form.Height - 16);

            Label titleLabel = new Label();
            titleLabel.AutoSize = false;
            titleLabel.Location = new Point(16, 14);
            titleLabel.Size = new Size(348, 24);
            titleLabel.ForeColor = Color.White;
            titleLabel.Font = new Font("Microsoft YaHei UI", 11f, FontStyle.Bold);
            titleLabel.Text = title;
            titleLabel.BackColor = Color.Transparent;

            Label bodyLabel = new Label();
            bodyLabel.AutoSize = false;
            bodyLabel.Location = new Point(16, 42);
            bodyLabel.Size = new Size(348, 56);
            bodyLabel.ForeColor = Color.FromArgb(220, 220, 220);
            bodyLabel.Font = new Font("Microsoft YaHei UI", 9f, FontStyle.Regular);
            bodyLabel.Text = body;
            bodyLabel.BackColor = Color.Transparent;

            Panel accent = new Panel();
            accent.Location = new Point(0, 0);
            accent.Size = new Size(4, form.Height);
            accent.BackColor = isError ? Color.FromArgb(232, 17, 35) : Color.FromArgb(16, 124, 16);

            form.Controls.Add(accent);
            form.Controls.Add(titleLabel);
            form.Controls.Add(bodyLabel);

            Timer timer = new Timer();
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
}
