package domain.validator;

import domain.BaseEntity;

public class BaseEntityValidator implements Validator {
    @Override
    public void validate(Object entity) throws ValidationException {
        if (!(entity instanceof BaseEntity)) {
            throw new ValidationException("entity not instance of BaseEntity");
        }
        BaseEntity baseEntity = (BaseEntity) entity;
        // validate id
        if (baseEntity.getID() == null
                || baseEntity.getID() < 0) {
            throw new ValidationException("id is invalid (null or negative)");
        }
    }
}
