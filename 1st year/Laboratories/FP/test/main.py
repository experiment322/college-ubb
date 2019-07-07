from repository.clienti_repository import ClientiRepository
from controller.clienti_controller import ClientiController
from ui import client_ui


def run():
    """Creeaza repository-ul si controller-ul pentru clienti si ruleaza ui-ul asociat"""
    repository = ClientiRepository("clienti.txt")
    controller = ClientiController(repository)
    client_ui.run(controller)


if __name__ == "__main__":
    run()
