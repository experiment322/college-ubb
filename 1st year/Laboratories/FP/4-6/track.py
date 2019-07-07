"""Module containing track structure manipulation functions"""


import copy


def create(size, initial_data):
    """
    > Create an empty track(rollback-capable object) and keep size snapshots of it.
    > initial_data is deep copied to avoid modifications in case of mutable objects.
    * `size` a number greater than 0
    * `initial_data` any object
    * :return: a track
    * *raises* ValueError
    """
    if int(size) < 1:
        raise ValueError
    return {
        "size": int(size),
        "data": [copy.deepcopy(initial_data)]
    }


def push(track, snapshot):
    """
    > Push the snapshot to the track and return the discarded snapshot if the track is full.
    > snapshot is deep copied to avoid modifications in case of mutable objects.
    * `track` a track
    * `snapshot` any object
    * :return: any object or None
    """
    track["data"].append(copy.deepcopy(snapshot))
    if len(track["data"]) > track["size"]:
        return track["data"].pop(0)


def pop(track):
    """
    > Pop the latest snapshot from the track and return it.
    > If the track contains only one snapshot keep it and return nothing.
    * `track` a track
    * :return: any object or None
    """
    if len(track["data"]) > 1:
        return track["data"].pop()


def peek(track):
    """
    > Return a deepcopy of the latest snapshot from the track.
    * `track` a track
    * :return: any object
    """
    return copy.deepcopy(track["data"][-1])
