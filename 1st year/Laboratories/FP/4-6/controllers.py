"""Module containing the controllers"""


from operator import mul, add
from itertools import accumulate
import track
import utils


def append_complex_number_to_list(list_track, item):
    list_snapshot = track.peek(list_track)
    list_snapshot.append(item)
    track.push(list_track, list_snapshot)


def insert_complex_number_at_index(list_track, item, index):
    list_snapshot = track.peek(list_track)
    list_snapshot.insert(index, item)
    track.push(list_track, list_snapshot)


def remove_complex_number_at_index(list_track, index):
    list_snapshot = track.peek(list_track)
    list_snapshot.pop(index)
    track.push(list_track, list_snapshot)


def remove_complex_numbers_sequence(list_track, index_left, index_right):
    list_snapshot = track.peek(list_track)
    list_snapshot[index_left:index_right + 1 or None] = []
    track.push(list_track, list_snapshot)


def replace_complex_number(list_track, old_item, new_item):
    list_snapshot = track.peek(list_track)
    list_snapshot = [new_item if item == old_item else item for item in list_snapshot]
    track.push(list_track, list_snapshot)


def print_imaginary_parts(list_track, index_left, index_right):
    list_snapshot = track.peek(list_track)
    list_sequence = list_snapshot[index_left:index_right + 1 or None]
    imaginary_parts = [item.imag for item in list_sequence]
    return imaginary_parts


def print_absolute_less_than_ten(list_track):
    list_snapshot = track.peek(list_track)
    list_sequence = [item for item in list_snapshot if abs(item) < 10]
    return list_sequence


def print_absolute_equal_with_ten(list_track):
    list_snapshot = track.peek(list_track)
    list_sequence = [item for item in list_snapshot if abs(item) == 10]
    return list_sequence


def print_complex_numbers_sum(list_track, index_left, index_right):
    list_snapshot = track.peek(list_track)
    list_sequence = list_snapshot[index_left:index_right + 1 or None]
    list_sum = None
    for result in accumulate(list_sequence, add):
        list_sum = result
    return list_sum


def print_complex_numbers_product(list_track, index_left, index_right):
    list_snapshot = track.peek(list_track)
    list_sequence = list_snapshot[index_left:index_right + 1 or None]
    list_product = None
    for result in accumulate(list_sequence, mul):
        list_product = result
    return list_product


def print_reverse_sorted_by_j(list_track):
    list_snapshot = track.peek(list_track)
    sorted_list = sorted(list_snapshot, key=lambda item: item.imag, reverse=True)
    return sorted_list


def filter_real_part_not_prime(list_track):
    list_snapshot = track.peek(list_track)
    list_snapshot = [
        item for item in list_snapshot
        if not utils.is_prime(item.real)
    ]
    track.push(list_track, list_snapshot)


def filter_by_absolute_relation(list_track, target, relation):
    list_snapshot = track.peek(list_track)
    list_snapshot = [
        item for item in list_snapshot
        if not utils.satisfies_relation(abs(item), target, relation)
    ]
    track.push(list_track, list_snapshot)


def undo_list_track(list_track):
    track.pop(list_track)
