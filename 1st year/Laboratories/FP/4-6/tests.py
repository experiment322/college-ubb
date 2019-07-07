"""Controllers unit tests"""


import unittest
import track
import controllers


class TestControllers(unittest.TestCase):
    """
    Unit test class for controllers.
    """

    def setUp(self):
        self.list_track = track.create(2, [1+1j, 2+2.5j, 3+0j])

    def test_append_complex_number_to_list(self):
        """
        Test controller append_complex_number_to_list.
        """
        controllers.append_complex_number_to_list(self.list_track, 1+0j)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j, 2+2.5j, 3+0j, 1+0j]
        )
        controllers.append_complex_number_to_list(self.list_track, 2+0j)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j, 2+2.5j, 3+0j, 1+0j, 2+0j]
        )

    def test_insert_complex_number_at_index(self):
        """
        Test controller insert_complex_number_at_index.
        """
        controllers.insert_complex_number_at_index(self.list_track, 1+0j, 0)
        self.assertEqual(
            track.peek(self.list_track),
            [1+0j, 1+1j, 2+2.5j, 3+0j]
        )
        controllers.insert_complex_number_at_index(self.list_track, 2+0j, 0)
        self.assertEqual(
            track.peek(self.list_track),
            [2+0j, 1+0j, 1+1j, 2+2.5j, 3+0j]
        )
        controllers.insert_complex_number_at_index(self.list_track, 3+0j, -100)
        self.assertEqual(
            track.peek(self.list_track),
            [3+0j, 2+0j, 1+0j, 1+1j, 2+2.5j, 3+0j]
        )
        controllers.insert_complex_number_at_index(self.list_track, 4+0j, 100)
        self.assertEqual(
            track.peek(self.list_track),
            [3+0j, 2+0j, 1+0j, 1+1j, 2+2.5j, 3+0j, 4+0j]
        )

    def test_remove_complex_number_at_index(self):
        """
        Test controller remove_complex_number_at_index.
        """
        controllers.remove_complex_number_at_index(self.list_track, 0)
        self.assertEqual(
            track.peek(self.list_track),
            [2+2.5j, 3+0j]
        )
        controllers.remove_complex_number_at_index(self.list_track, 1)
        self.assertEqual(
            track.peek(self.list_track),
            [2+2.5j]
        )
        with self.assertRaises(IndexError):
            controllers.remove_complex_number_at_index(self.list_track, 1)

    def test_remove_complex_numbers_sequence(self):
        """
        Test controller remove_complex_numbers_sequence.
        """
        controllers.remove_complex_numbers_sequence(self.list_track, 1, 2)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j]
        )
        track.push(self.list_track, [1+1j, 2+2.5j, 3+0j])
        controllers.remove_complex_numbers_sequence(self.list_track, -2, -1)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j]
        )
        track.push(self.list_track, [1+1j, 2+2.5j, 3+0j])
        controllers.remove_complex_numbers_sequence(self.list_track, -10, 1)
        self.assertEqual(
            track.peek(self.list_track),
            [3+0j]
        )

    def test_replace_complex_number(self):
        """
        Test controller replace_complex_number.
        """
        controllers.replace_complex_number(self.list_track, 1+1j, 2+2.5j)
        self.assertEqual(
            track.peek(self.list_track),
            [2+2.5j, 2+2.5j, 3+0j]
        )
        controllers.replace_complex_number(self.list_track, 2+2.5j, 3+0j)
        self.assertEqual(
            track.peek(self.list_track),
            [3+0j, 3+0j, 3+0j]
        )
        controllers.replace_complex_number(self.list_track, 1+0j, 2+0j)
        self.assertEqual(
            track.peek(self.list_track),
            [3+0j, 3+0j, 3+0j]
        )

    def test_print_imaginary_parts(self):
        """
        Test controller print_imaginary_parts.
        """
        self.assertEqual(
            controllers.print_imaginary_parts(self.list_track, 0, 2),
            [1.0, 2.5, 0.0]
        )
        self.assertEqual(
            controllers.print_imaginary_parts(self.list_track, -2, 100),
            [2.5, 0.0]
        )

    def test_print_absolute_less_than_ten(self):
        """
        Test controller print_absolute_less_than_ten.
        """
        self.assertEqual(
            controllers.print_absolute_less_than_ten(self.list_track),
            [1+1j, 2+2.5j, 3+0j]
        )
        track.push(self.list_track, [9+5j, 0+10j, 8+4j, 10+0j])
        self.assertEqual(
            controllers.print_absolute_less_than_ten(self.list_track),
            [8+4j]
        )

    def test_print_absolute_equal_with_ten(self):
        """
        Test controller print_absolute_equal_with_ten.
        """
        self.assertEqual(
            controllers.print_absolute_equal_with_ten(self.list_track),
            []
        )
        track.push(self.list_track, [9+5j, 0+10j, 8+5j, 10+0j])
        self.assertEqual(
            controllers.print_absolute_equal_with_ten(self.list_track),
            [0+10j, 10+0j]
        )

    def test_print_complex_numbers_sum(self):
        """
        Test controller print_complex_numbers_sum.
        """
        self.assertEqual(
            controllers.print_complex_numbers_sum(self.list_track, 0, 100),
            6+3.5j
        )
        track.push(self.list_track, [])
        self.assertEqual(
            controllers.print_complex_numbers_sum(self.list_track, -1000, 100),
            None
        )

    def test_print_complex_numbers_product(self):
        """
        Test controller print_complex_numbers_product.
        """
        self.assertEqual(
            controllers.print_complex_numbers_product(self.list_track, 0, 1),
            -0.5+4.5j
        )
        track.push(self.list_track, [])
        self.assertEqual(
            controllers.print_complex_numbers_product(self.list_track, -1000, 100),
            None
        )

    def test_print_reverse_sorted_by_j(self):
        """
        Test controller print_reverse_sorted_by_j.
        """
        self.assertEqual(
            controllers.print_reverse_sorted_by_j(self.list_track),
            [2+2.5j, 1+1j, 3+0j]
        )

    def test_filter_real_part_not_prime(self):
        """
        Test controller filter_real_part_not_prime.
        """
        controllers.filter_real_part_not_prime(self.list_track)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j]
        )

    def test_filter_by_absolute_relation(self):
        """
        Test controller filter_by_absolute_relation.
        """
        controllers.filter_by_absolute_relation(self.list_track, 3, 0)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j, 2+2.5j]
        )
        track.push(self.list_track, [1+1j, 2+2.5j, 3+0j])
        controllers.filter_by_absolute_relation(self.list_track, 2, -999)
        self.assertEqual(
            track.peek(self.list_track),
            [2+2.5j, 3+0j]
        )
        track.push(self.list_track, [1+1j, 2+2.5j, 3+0j])
        controllers.filter_by_absolute_relation(self.list_track, 3, 12321)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j, 3+0j]
        )

    def test_undo_list_track(self):
        """
        Test controller undo_list_track.
        """
        controllers.undo_list_track(self.list_track)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j, 2+2.5j, 3+0j]
        )
        track.push(self.list_track, [3+0j])
        controllers.undo_list_track(self.list_track)
        self.assertEqual(
            track.peek(self.list_track),
            [1+1j, 2+2.5j, 3+0j]
        )


unittest.main()
