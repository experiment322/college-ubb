package utils;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class WeekUtils {
    private List<Calendar> didacticWeeks = new ArrayList<>(28);

    public WeekUtils(String dateFormat, String dateSeparator, List<String> didacticPeriods) {
        SimpleDateFormat dateParser = new SimpleDateFormat(dateFormat);
        for (String didacticPeriod : didacticPeriods) {
            String interval = didacticPeriod.replaceAll("\\s+", "");
            try {
                Date intervalBeg = dateParser.parse(interval.split(Pattern.quote(dateSeparator))[0]);
                Date intervalEnd = dateParser.parse(interval.split(Pattern.quote(dateSeparator))[1]);
                Calendar i = Calendar.getInstance(), l = Calendar.getInstance();
                for (i.setTime(intervalBeg), l.setTime(intervalEnd); !i.after(l); i.add(Calendar.DATE, 7)) {
                    didacticWeeks.add((Calendar) i.clone());
                }
            } catch (ParseException e) {
                throw new IllegalArgumentException("didacticPeriods contains invalid dates or dateFormat is malformed");
            }
        }
        if (didacticWeeks.size() != 28) {
            throw new IllegalArgumentException("didacticPeriods should span a 28 weeks period");
        }
    }

    public Integer getCurrentDidacticWeek() {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(new Date());
        return getDidacticWeekForCalendar(calendar);
    }

    public Calendar getCalendarForDidacticWeek(Integer didacticWeek) {
        return (Calendar) didacticWeeks.get(didacticWeek - 1).clone();
    }

    private Integer getDidacticWeekForCalendar(Calendar calendar) {
        Integer calendarWeek = calendar.get(Calendar.WEEK_OF_YEAR);
        List<Integer> didacticCalendarWeeks = didacticWeeks.stream()
                .mapToInt(c -> c.get(Calendar.WEEK_OF_YEAR))
                .boxed()
                .collect(Collectors.toList());
        if (didacticCalendarWeeks.indexOf(calendarWeek) != -1) {
            return didacticCalendarWeeks.indexOf(calendarWeek) + 1;
        }
        return 0;
    }
}
