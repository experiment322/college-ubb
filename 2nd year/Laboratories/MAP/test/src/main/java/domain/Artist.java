package domain;

import java.util.Objects;
import java.util.StringJoiner;

public class Artist implements HasId<Long> {
    private Long id;
    private String nume;
    private Integer varsta;
    private String genMuzical;

    public Artist() {
    }

    public Long getId() {
        return this.id;
    }

    public String getNume() {
        return this.nume;
    }

    public Integer getVarsta() {
        return this.varsta;
    }

    public String getGenMuzical() {
        return this.genMuzical;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public void setVarsta(Integer varsta) {
        this.varsta = varsta;
    }

    public void setGenMuzical(String genMuzical) {
        this.genMuzical = genMuzical;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Artist artist = (Artist) o;
        return Objects.equals(id, artist.id) &&
                Objects.equals(nume, artist.nume) &&
                Objects.equals(varsta, artist.varsta) &&
                Objects.equals(genMuzical, artist.genMuzical);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, nume, varsta, genMuzical);
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", Artist.class.getSimpleName() + "[", "]")
                .add("id=" + id)
                .add("nume='" + nume + "'")
                .add("varsta=" + varsta)
                .add("genMuzical='" + genMuzical + "'")
                .toString();
    }
}
