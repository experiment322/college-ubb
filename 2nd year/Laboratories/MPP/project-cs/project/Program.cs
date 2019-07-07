using System;
using log4net.Config;
using project.repository;

namespace project
{
    internal static class Program
    {
        public static void Main()
        {
            BasicConfigurator.Configure();

            var repository = new AthleteRepository();
            foreach (var athlete in repository.FindAll())
            {
                Console.WriteLine(athlete);
            }

            var athleteRepository = new AthleteRepository();
            foreach (var athlete in athleteRepository.FindAll())
            {
                Console.WriteLine(athlete);
            }
        }
    }
}