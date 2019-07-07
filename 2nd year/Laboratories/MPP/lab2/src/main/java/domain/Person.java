package domain;

public class Person {
    private Integer id;
    private Integer age;
    private String name;

    public Person(Integer id, Integer age, String name) {
        this.id = id;
        this.age = age;
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Person person = (Person) o;

        if (!id.equals(person.id)) return false;
        if (!age.equals(person.age)) return false;
        return name.equals(person.name);
    }

    @Override
    public int hashCode() {
        int result = id.hashCode();
        result = 31 * result + age.hashCode();
        result = 31 * result + name.hashCode();
        return result;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
