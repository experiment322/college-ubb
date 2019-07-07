using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CRUD.UI.Tui
{
    public abstract class BaseTui : IUi
    {
        private const string ExitOption = "EXIT";
        private const string TitlePrefix = "# ";
        private const string OptionPrefix = "- ";
        private const string OptionPrompt = "> ";
        private const string InvalidOption = "Invalid option...";
        private const string ContinuePrompt = "Press any key to continue...";

        private string _tui;
        private IDictionary<string, Action> _tuiActions;

        protected void Initialize(string tuiTitle, IDictionary<string, Action> tuiActions)
        {
            var tui = new StringBuilder();
            tui.Append(TitlePrefix).Append(tuiTitle).AppendLine();
            foreach (var key in tuiActions.Keys.Append(ExitOption))
            {
                tui.Append(OptionPrefix).Append(key).AppendLine();
            }

            tui.Append(OptionPrompt);
            _tui = tui.ToString();
            _tuiActions = tuiActions;
        }

        protected static string GenerateMessage(bool didOperationSucceed)
        {
            return didOperationSucceed ? "✓" : "✗";
        }

        protected static string Read(string key)
        {
            Console.Write($"{key}: ");
            return Console.ReadLine();
        }

        protected static IDictionary<string, string> Read(params string[] keys)
        {
            var dictionary = new Dictionary<string, string>();
            foreach (var key in keys)
            {
                dictionary[key] = Read(key);
            }

            return dictionary;
        }

        protected static void Write(string line)
        {
            Console.WriteLine(line);
        }

        private bool Loop()
        {
            Console.Write(_tui);
            var input = Console.ReadLine();
            if (input == ExitOption)
            {
                return false;
            }

            foreach (var key in _tuiActions.Keys)
            {
                if (string.IsNullOrEmpty(input))
                {
                    break;
                }

                if (!key.ToLower().Contains(input.ToLower())) continue;
                Console.WriteLine($"{OptionPrompt}{key}");
                _tuiActions[key].Invoke();
                return true;
            }

            Console.WriteLine($"{InvalidOption}");
            return true;
        }

        public void Run()
        {
            var running = true;
            while (running)
            {
                Console.WriteLine();
                try
                {
                    running = Loop();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"{e.GetType().Name}:\n\t{e.Message}");
                }
                finally
                {
                    if (running)
                    {
                        Console.WriteLine(ContinuePrompt);
                        Console.ReadKey(true);
                    }
                }
            }
        }
    }
}