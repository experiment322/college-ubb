package domain;

import java.util.Objects;

public class Homework extends BaseEntity {
    private Integer deadlineWeek;
    private Integer assignmentWeek;
    private String description;

    public Homework(Integer id, Integer deadlineWeek, Integer assignmentWeek, String description) {
        super(id);
        this.deadlineWeek = deadlineWeek;
        this.assignmentWeek = assignmentWeek;
        this.description = description;
    }

    public Homework(Homework homework) {
        super(homework);
        deadlineWeek = homework.deadlineWeek;
        assignmentWeek = homework.assignmentWeek;
        description = homework.description;
    }

    public Integer getDeadlineWeek() {
        return deadlineWeek;
    }

    public void setDeadlineWeek(Integer deadlineWeek) {
        this.deadlineWeek = deadlineWeek;
    }

    public Integer getAssignmentWeek() {
        return assignmentWeek;
    }

    public void setAssignmentWeek(Integer assignmentWeek) {
        this.assignmentWeek = assignmentWeek;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Homework homework = (Homework) o;
        return Objects.equals(deadlineWeek, homework.deadlineWeek) &&
                Objects.equals(assignmentWeek, homework.assignmentWeek) &&
                Objects.equals(description, homework.description);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), deadlineWeek, assignmentWeek, description);
    }

    @Override
    public String toString() {
        return super.toString() +
                "|deadlineWeek=" + deadlineWeek +
                "|assignmentWeek=" + assignmentWeek +
                "|description=" + description;
    }
}
