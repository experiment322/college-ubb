package domain.validator;

public interface Validator {
    /**
     * The implementation should cast the entity to the desired type
     * and throw a validation exception if it is malformed
     *
     * @param entity entity
     * @throws ValidationException exception
     */
    void validate(Object entity) throws ValidationException;
}
