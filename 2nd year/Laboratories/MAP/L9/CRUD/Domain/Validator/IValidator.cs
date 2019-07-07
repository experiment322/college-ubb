namespace CRUD.Domain.Validator
{
    public interface IValidator<in TEntity, TId> where TEntity : IHasId<TId>
    {
        void Validate(TEntity entity);
    }
}