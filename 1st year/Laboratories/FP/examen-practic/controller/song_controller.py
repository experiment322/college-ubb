from domain.song import Song
from random import random
from math import trunc


class SongController:
    def __init__(self, repository, validator):
        self._repository = repository
        self._validator = validator

    def add_song(self, dto):
        """
        Convert dto to song and add it to repository after successful validation.
        If there is already a song with the artist-title combination in dto ValueError will be raised.
        dto="title,artist,genre,playtime"
        """
        song = Song("", "", "", "").from_string(dto)
        if not self._validator.validate(song):
            raise ValueError("Invalid song details")
        self._repository.add(song)

    def mod_song(self, dto):
        """
        Convert dto to song and after successful validation modify the playtime and genre of the song with
        artist-title combination found in dto.
        If there isn't a song with this combination ValueError will be raised.
        dto="title,artist,genre,playtime"
        """
        song = Song("", "", "", "").from_string(dto)
        if not self._validator.validate(song):
            raise ValueError("Invalid song details")
        self._repository.mod(song)

    def generate_songs(self, dto):
        """
        Generate dto random songs and add them to the repository. dto must be a positive integer as string.
        dto="number"
        """
        if int(dto) < 1:
            raise ValueError("Invalid number")

        def random_chr(j):
            v = ["a", "e", "i", "o", "u"]
            c = ["b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "w", "x", "y", "z"]
            return v[trunc(random() * len(v))] if j % 2 == 0 else c[trunc(random() * len(c))]
        genres = ["Rock", "Pop", "Jazz", "Altele"]
        for i in range(int(dto)):
            artist_len1 = trunc(random() * 8 + 1)
            artist_len2 = trunc(random() * 8 + 1)
            title_len1 = trunc(random() * 16 + 1)
            title_len2 = trunc(random() * 16 + 1)
            artist = "".join(
                [random_chr(i) for i in range(artist_len1)] + [" "] + [random_chr(i) for i in range(artist_len2)])
            title = "".join(
                [random_chr(i) for i in range(title_len1)] + [" "] + [random_chr(i) for i in range(title_len2)])
            duration = trunc(random() * 500)
            genre = genres[trunc(random() * len(genres))]
            song = Song(title, artist, genre, duration)
            self._repository.add(song)

    def export_songs(self, dto):
        """
        Sort the songs in repository by artist and title and export them to the file with name dto.
        dto="filename"
        """
        songs = self._repository.get_all()
        songs = sorted(songs, key=lambda s: s.get_artist().lower())
        songs = sorted(songs, key=lambda s: s.get_title().lower())
        with open(dto, "w") as file:
            for song in songs:
                file.write("{}\n".format(song.to_string()))
