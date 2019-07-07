class SongValidator:
    @staticmethod
    def validate(song):
        """
        Return false if song is not instance of Song, its genre is not Rock, Pop, Jazz or Altele or if playtime
        is not a natural number. Else return True.
        """
        if not isinstance(song, Song):
            return False
        if song.get_genre() not in ["Rock", "Pop", "Jazz", "Altele"]:
            return False
        try:
            if int(song.get_playtime()) < 0:
                return False
        except ValueError:
            return False
        return True


class Song:
    def __init__(self, title, artist, genre, playtime):
        self._title = title
        self._artist = artist
        self._genre = genre
        self._playtime = playtime

    def get_title(self): return self._title

    def set_title(self, title): self._title = title

    def get_artist(self): return self._artist

    def set_artist(self, artist): self._artist = artist

    def get_genre(self): return self._genre

    def set_genre(self, genre): self._genre = genre

    def get_playtime(self): return self._playtime

    def set_playtime(self, playtime): self._playtime = playtime

    def to_string(self):
        """Convert song to CSV format and return it as a string."""
        return "{},{},{},{}".format(self._artist, self._title, self._playtime, self._genre)

    def from_string(self, s):
        """Read song data from CSV string. Return self for constructor chaining."""
        self._artist, self._title, self._playtime, self._genre = s.split(",")
        return self
