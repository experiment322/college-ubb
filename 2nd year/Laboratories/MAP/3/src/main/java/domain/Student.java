package domain;

import java.util.Objects;

public class Student extends BaseEntity {
    private Integer group;
    private String name;
    private String email;
    private String teacherName;

    public Student(Integer id, Integer group, String name, String email, String teacherName) {
        super(id);
        this.group = group;
        this.name = name;
        this.email = email;
        this.teacherName = teacherName;
    }

    public Student(Student student) {
        super(student);
        group = student.group;
        name = student.name;
        email = student.email;
        teacherName = student.teacherName;
    }

    public Integer getGroup() {
        return group;
    }

    public void setGroup(Integer group) {
        this.group = group;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getTeacherName() {
        return teacherName;
    }

    public void setTeacherName(String teacherName) {
        this.teacherName = teacherName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Student student = (Student) o;
        return Objects.equals(group, student.group) &&
                Objects.equals(name, student.name) &&
                Objects.equals(email, student.email) &&
                Objects.equals(teacherName, student.teacherName);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), group, name, email, teacherName);
    }

    @Override
    public String toString() {
        return super.toString() +
                "|group=" + group +
                "|name='" + name +
                "|email='" + email +
                "|teacherName='" + teacherName;
    }
}
