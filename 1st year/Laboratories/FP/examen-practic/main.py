from repository.song_repository import SongFileRepository
from controller.song_controller import SongController
from domain.song import SongValidator
from ui.song_ui import song_ui


def main():
    repository = SongFileRepository("songs.txt")
    controller = SongController(repository, SongValidator)
    song_ui(controller)


if __name__ == "__main__":
    main()
