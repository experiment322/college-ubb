using System.Collections.Generic;

namespace project.repository
{
    public interface IRepository<in TId, TEntity>
    {
        TEntity FindOne(TId id);
        IEnumerable<TEntity> FindAll();
        void Save(TEntity entity);
        void Update(TEntity entity);
        void Delete(TId id);
    }
}