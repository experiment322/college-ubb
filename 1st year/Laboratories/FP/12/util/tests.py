import unittest
from util.sorting import sorted_custom


class TestSortedCustom(unittest.TestCase):
    def setUp(self):
        self.array = [14, 46, 43, 27, 57, 41, 45, 21, 70]
        self.sorted_array = [14, 21, 27, 41, 43, 45, 46, 57, 70]

    def test_bubble_sort(self):
        result = sorted_custom(self.array, "bubble")
        self.assertEqual(result, self.sorted_array)

    def test_shell_sort(self):
        result = sorted_custom(self.array, "shell")
        self.assertEqual(result, self.sorted_array)
