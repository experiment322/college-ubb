namespace CRUD.Domain
{
    public interface IHasId<TId>
    {
        TId Id { get; set; }
    }
}