package domain;

import java.util.Objects;
import java.util.StringJoiner;

public class Fan implements HasId<Long> {
    private Long id;
    private String nume;

    public Fan() {
    }

    public Long getId() {
        return this.id;
    }

    public String getNume() {
        return this.nume;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Fan fan = (Fan) o;
        return Objects.equals(id, fan.id) &&
                Objects.equals(nume, fan.nume);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, nume);
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", Fan.class.getSimpleName() + "[", "]")
                .add("id=" + id)
                .add("nume='" + nume + "'")
                .toString();
    }
}
