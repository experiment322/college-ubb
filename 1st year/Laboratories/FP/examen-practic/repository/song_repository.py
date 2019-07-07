from domain.song import Song
from os import remove, rename


class SongFileRepository:
    def __init__(self, filename):
        self._filename = filename

    def add(self, entity):
        """Add entity to repository. If there is a song with entity's title and author ValueError will be raised."""
        with open(self._filename, "r") as file:
            for line in file:
                song = Song("", "", "", "").from_string(line.strip())
                if song.get_artist() == entity.get_artist() and \
                        song.get_title() == entity.get_title():
                    raise ValueError("Song already exists")
        with open(self._filename, "a") as file:
            file.write("{}\n".format(entity.to_string()))

    def mod(self, entity):
        """
        Modify an existing entity.
        If the artist-title combination of entity is not found ValueError will be raised.
        """
        found = False
        with open(self._filename, "r") as file:
            with open("temp.txt", "w") as temp_file:
                for line in file:
                    target = song = Song("", "", "", "").from_string(line.strip())
                    if song.get_artist() == entity.get_artist() and \
                            song.get_title() == entity.get_title():
                        found, target = True, entity
                    temp_file.write("{}\n".format(target.to_string()))
        remove(self._filename)
        rename("temp.txt", self._filename)
        if not found:
            raise ValueError("Song not found")

    def get_all(self):
        """Return a list of all the songs as Song instances."""
        result = []
        with open(self._filename, "r") as file:
            for line in file:
                song = Song("", "", "", "").from_string(line.strip())
                result.append(song)
        return result
