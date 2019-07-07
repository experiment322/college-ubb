using System;
using System.Collections.Generic;
using CRUD.Domain;
using CRUD.Domain.Validator;

namespace CRUD.Repository
{
    public class InMemoryRepository<TId, TEntity> : ICrudRepository<TId, TEntity> where TEntity : IHasId<TId>
    {
        private readonly IValidator<TEntity, TId> _validator;
        private readonly Dictionary<TId, TEntity> _entities;

        public InMemoryRepository(IValidator<TEntity, TId> validator, Dictionary<TId, TEntity> entities)
        {
            _validator = validator;
            _entities = entities;
        }

        public TEntity Save(TEntity entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException(nameof(entity));
            }

            _validator.Validate(entity);
            if (_entities.ContainsKey(entity.Id))
            {
                return entity;
            }

            _entities[entity.Id] = entity;
            return default(TEntity);
        }

        public TEntity Update(TEntity entity)
        {
            if (entity == null)
            {
                throw new ArgumentNullException(nameof(entity));
            }

            _validator.Validate(entity);
            if (!_entities.ContainsKey(entity.Id))
            {
                return entity;
            }

            _entities[entity.Id] = entity;
            return default(TEntity);
        }

        public TEntity Delete(TId id)
        {
            if (id == null)
            {
                throw new ArgumentNullException(nameof(id));
            }

            if (!_entities.ContainsKey(id))
            {
                return default(TEntity);
            }

            var entity = _entities[id];
            _entities.Remove(id);
            return entity;
        }

        public TEntity FindOne(TId id)
        {
            if (id == null)
            {
                throw new ArgumentNullException(nameof(id));
            }

            _entities.TryGetValue(id, out var entity);
            return entity;
        }

        public ICollection<TEntity> FindAll()
        {
            return _entities.Values;
        }
    }
}