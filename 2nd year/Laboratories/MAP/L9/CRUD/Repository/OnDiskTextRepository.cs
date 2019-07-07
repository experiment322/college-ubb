using System.Collections.Generic;
using System.IO;
using System.Linq;
using CRUD.Domain;
using CRUD.Domain.Validator;
using CRUD.Utils;

namespace CRUD.Repository
{
    public class OnDiskTextRepository<TId, TEntity> : ICrudRepository<TId, TEntity> where TEntity : IHasId<TId>
    {
        private readonly string _file;
        private readonly InMemoryRepository<TId, TEntity> _repository;

        public OnDiskTextRepository(IValidator<TEntity, TId> validator, Dictionary<TId, TEntity> entities, string file)
        {
            _file = file;
            _repository = new InMemoryRepository<TId, TEntity>(validator, entities);

            if (!File.Exists(_file))
            {
                File.CreateText(_file).Close();
            }

            LoadData();
        }

        private void LoadData()
        {
            foreach (var line in File.ReadAllLines(_file))
            {
                _repository.Save(EntityUtils.FromString<TEntity, TId>(line));
            }
        }

        private void DumpData()
        {
            File.WriteAllLines(_file,
                _repository.FindAll().Select(EntityUtils.DumpString<TEntity, TId>)
            );
        }

        public TEntity Save(TEntity entity)
        {
            var result = _repository.Save(entity);
            if (result == null) DumpData();
            return result;
        }

        public TEntity Update(TEntity entity)
        {
            var result = _repository.Update(entity);
            if (result == null) DumpData();
            return result;
        }

        public TEntity Delete(TId id)
        {
            var result = _repository.Delete(id);
            if (result != null) DumpData();
            return result;
        }

        public TEntity FindOne(TId id)
        {
            return _repository.FindOne(id);
        }

        public ICollection<TEntity> FindAll()
        {
            return _repository.FindAll();
        }
    }
}