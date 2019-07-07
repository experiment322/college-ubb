package domain;

import lombok.Data;

import java.math.BigInteger;

@Data
public class Student implements HasId<Integer> {
    private Integer id;
    private Integer group;
    private String name;
    private String email;
    private String teacherName;
    private BigInteger absences;
    private BigInteger justifiedAbsences;
}
