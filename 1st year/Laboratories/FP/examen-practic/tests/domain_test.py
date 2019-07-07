from domain.song import Song


def test_to_string():
    assert Song("title", "artist", "Rock", "120").to_string() == "artist,title,120,Rock"


def test_from_string():
    song = Song("", "", "", "").from_string("artist,title,120,Jazz")
    assert song.get_artist() == "artist"
    assert song.get_title() == "title"
    assert song.get_playtime() == "120"
    assert song.get_genre() == "Jazz"


if __name__ == "__main__":
    test_to_string()
    test_from_string()
