from repository.song_repository import SongFileRepository
from domain.song import Song
from os import remove


def test_add():
    remove("test_repo.txt")
    repository = SongFileRepository("test_repo.txt")
    repository.add(Song("a", "b", "c", "d"))
    with open("test_repo.txt", "r") as file:
        line = file.readline().strip()
    assert line == "b,a,d,c"


if __name__ == "__main__":
    test_add()
