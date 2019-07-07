using System;

namespace CRUD.Domain.Validator
{
    public class ValidationException : Exception
    {
        public ValidationException(string message) : base(message)
        {
        }
    }
}