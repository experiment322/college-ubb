using System.Collections.Generic;
using CRUD.Domain;

namespace CRUD.Repository
{
    public interface ICrudRepository<in TId, TEntity> where TEntity : IHasId<TId>
    {
        TEntity Save(TEntity entity);
        TEntity Update(TEntity entity);
        TEntity Delete(TId id);
        TEntity FindOne(TId id);
        ICollection<TEntity> FindAll();
    }
}