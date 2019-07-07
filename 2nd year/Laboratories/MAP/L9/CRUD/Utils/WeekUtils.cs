using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text.RegularExpressions;

namespace CRUD.Utils
{
    public class WeekUtils
    {
        public const int SemesterWeekSpan = 14;

        private readonly CultureInfo _cultureInfo;
        private readonly DateTime[] _didacticWeeks = new DateTime[SemesterWeekSpan];

        public WeekUtils(string locale, char dateSeparator, IEnumerable<string> didacticPeriods)
        {
            _cultureInfo = new CultureInfo(locale);

            var currentWeek = 0;
            foreach (var didacticPeriod in didacticPeriods)
            {
                var period = Regex.Replace(didacticPeriod, "\\s+", "");
                var intervalBeg = DateTime.Parse(period.Split(dateSeparator)[0], _cultureInfo);
                var intervalEnd = DateTime.Parse(period.Split(dateSeparator)[1], _cultureInfo);

                for (var i = intervalBeg; i.CompareTo(intervalEnd) <= 0; i = i.AddDays(7))
                {
                    if (currentWeek >= SemesterWeekSpan)
                    {
                        throw new ArgumentException(nameof(didacticPeriods) + $" must span {SemesterWeekSpan} weeks");
                    }

                    _didacticWeeks[currentWeek++] = i;
                }
            }

            if (currentWeek < SemesterWeekSpan)
            {
                throw new ArgumentException(nameof(didacticPeriods) + $" must span {SemesterWeekSpan} weeks");
            }
        }

        public int GetCurrentDidacticWeek()
        {
            return GetDidacticWeekForDateTime(DateTime.Today);
        }

//        private DateTime GetDateTimeForDidacticWeek(int didacticWeek)
//        {
//            return _didacticWeeks[didacticWeek - 1];
//        }

        private int GetDidacticWeekForDateTime(DateTime dateTime)
        {
            var weekRule = _cultureInfo.DateTimeFormat.CalendarWeekRule;
            var firstDayOfWeek = _cultureInfo.DateTimeFormat.FirstDayOfWeek;

            var calendarWeek = _cultureInfo.Calendar.GetWeekOfYear(dateTime, weekRule, firstDayOfWeek);
            var didacticCalendarWeeks = _didacticWeeks
                .Select(time => _cultureInfo.Calendar.GetWeekOfYear(time, weekRule, firstDayOfWeek))
                .ToArray();

            if (didacticCalendarWeeks.Contains(calendarWeek))
            {
                return Array.IndexOf(didacticCalendarWeeks, calendarWeek) + 1;
            }

            return 0;
        }
    }
}