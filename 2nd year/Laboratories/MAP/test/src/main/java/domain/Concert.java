package domain;

import java.time.LocalDate;
import java.util.Objects;
import java.util.StringJoiner;

public class Concert implements HasId<Object> {
    private Object id;
    private Artist artist;
    private Fan fan;
    private LocalDate dataConcert;

    public Concert() {
    }

    public Object getId() {
        return this.id;
    }

    public Artist getArtist() {
        return this.artist;
    }

    public Fan getFan() {
        return this.fan;
    }

    public LocalDate getDataConcert() {
        return this.dataConcert;
    }

    public void setId(Object id) {
        this.id = id;
    }

    public void setArtist(Artist artist) {
        this.artist = artist;
    }

    public void setFan(Fan fan) {
        this.fan = fan;
    }

    public void setDataConcert(LocalDate dataConcert) {
        this.dataConcert = dataConcert;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Concert concert = (Concert) o;
        return Objects.equals(id, concert.id) &&
                Objects.equals(artist, concert.artist) &&
                Objects.equals(fan, concert.fan) &&
                Objects.equals(dataConcert, concert.dataConcert);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, artist, fan, dataConcert);
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", Concert.class.getSimpleName() + "[", "]")
                .add("artist=" + artist)
                .add("fan=" + fan)
                .add("dataConcert=" + dataConcert)
                .toString();
    }
}
