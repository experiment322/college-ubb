package domain;

public interface HasId<ID> {
    /**
     * ID getter
     *
     * @return ID value
     */
    ID getId();

    /**
     * ID setter
     *
     * @param id new ID
     */
    void setId(ID id);
}
