package domain.validator;

public interface Validator {
    /**
     * @param entity entity
     * @throws ValidationException exception
     */
    void validate(Object entity) throws ValidationException;
}
