using System;
using System.Linq;
using System.Reflection;
using CRUD.Domain;

namespace CRUD.Utils
{
    public static class EntityUtils
    {
        private const char IllegalCharacter = '?';
        private const char ColumnSeparator = '|';
        private const char ColumnMapper = '=';

        private static string SanitizeString(string str)
        {
            return str?
                .Replace(ColumnMapper, IllegalCharacter)
                .Replace(ColumnSeparator, IllegalCharacter);
        }

        private static PropertyInfo[] GetRwProperties(Type type)
        {
            return type.GetProperties()
                .Where(property => property.CanRead &&
                                   property.CanWrite &&
                                   Attribute.IsDefined(property, typeof(PropertySequence)))
                .OrderBy(property => ((PropertySequence) property
                    .GetCustomAttributes(typeof(PropertySequence))
                    .Single()).Value)
                .ThenBy(property => property.Name)
                .ToArray();
        }

        public static TEntity Clone<TEntity, TId>(TEntity entity) where TEntity : IHasId<TId>
        {
            var properties = GetRwProperties(typeof(TEntity));
            var clone = (TEntity) Activator.CreateInstance(typeof(TEntity));

            foreach (var property in properties)
            {
                property.SetValue(clone, property.GetValue(entity));
            }

            return clone;
        }

        public static string DumpString<TEntity, TId>(TEntity entity) where TEntity : IHasId<TId>
        {
            var properties = GetRwProperties(typeof(TEntity));
            var columns = new string[properties.Length];

            for (var i = 0; i < properties.Length; i++)
            {
                var columnName = properties[i].Name;
                var columnValue = properties[i].PropertyType != typeof(string)
                    ? SanitizeString(properties[i].GetValue(entity).ToString())
                    : SanitizeString(properties[i].GetValue(entity) as string);

                columns[i] = columnName + ColumnMapper + columnValue;
            }

            return string.Join(ColumnSeparator.ToString(), columns);
        }

        public static TEntity FromString<TEntity, TId>(string str) where TEntity : IHasId<TId>
        {
            var properties = GetRwProperties(typeof(TEntity));
            var columns = str.Split(new[] {ColumnSeparator}, StringSplitOptions.RemoveEmptyEntries);
            var entity = (TEntity) Activator.CreateInstance(typeof(TEntity));

            foreach (var column in columns)
            {
                var columnEntry = column.Split(new[] {ColumnMapper}, 2);
                if (columnEntry.Length != 2) throw new FormatException(column);

                var columnName = columnEntry[0];
                var columnValue = SanitizeString(columnEntry[1]);

                var property = Array.Find(properties, prop => prop.Name == columnName);
                if (property == null) throw new ArgumentOutOfRangeException(columnName);

                object propertyValue;
                if (property.PropertyType != typeof(string))
                {
                    var propertyParser = property.PropertyType.GetMethod("Parse", new[] {typeof(string)});
                    if (propertyParser == null) throw new ArgumentNullException(nameof(propertyParser));
                    propertyValue = propertyParser.Invoke(null, new object[] {columnValue});
                }
                else
                {
                    propertyValue = columnValue;
                }

                property.SetValue(entity, propertyValue);
            }

            return entity;
        }

        [AttributeUsage(AttributeTargets.Property)]
        public class PropertySequence : Attribute
        {
            public int Value { get; }

            public PropertySequence(int value)
            {
                Value = value;
            }
        }
    }
}