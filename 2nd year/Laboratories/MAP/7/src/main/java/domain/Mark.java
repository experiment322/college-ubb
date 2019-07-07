package domain;

import lombok.Data;

@Data
public class Mark implements HasId<String> {
    private String id;
    private Double value;
    private Integer week;
    private String feedback;

    public Integer getTaskId() {
        return Integer.valueOf(id.split("~")[0]);
    }

    public Integer getStudentId() {
        return Integer.valueOf(id.split("~")[1]);
    }

    public void setId(String id) {
        setId(
                Integer.valueOf(id.split("~")[0]),
                Integer.valueOf(id.split("~")[1])
        );
    }

    public void setId(Integer taskId, Integer studentId) {
        this.id = taskId.toString() + "~" + studentId.toString();
    }
}
