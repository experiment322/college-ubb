package domain;

import lombok.Data;

@Data
public class Task implements HasId<Integer> {
    private Integer id;
    private Integer assignmentWeek;
    private Integer deadlineWeek;
    private String description;
}
