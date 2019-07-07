package domain;

import java.util.Objects;

public class BaseEntity implements HasID<Integer> {
    private Integer id;

    public BaseEntity(Integer id) {
        this.id = id;
    }

    BaseEntity(BaseEntity entity) {
        id = entity.id;
    }

    @Override
    public Integer getID() {
        return id;
    }

    @Override
    public void setID(Integer id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BaseEntity that = (BaseEntity) o;
        return Objects.equals(id, that.id);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public String toString() {
        return "id=" + id;
    }
}
