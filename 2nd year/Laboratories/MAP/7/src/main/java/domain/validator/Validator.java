package domain.validator;

public interface Validator<E> {
    /**
     * The implementation should throw a validation exception if entity is malformed
     *
     * @param entity entity
     * @throws ValidationException exception
     */
    void validate(E entity) throws ValidationException;
}
