import os
import unittest
from domain.entity import Entity
from domain.student import Student
from domain.relation import Relation
from repository.entity_dict_repository import EntityDictRepository
from repository.entity_file_repository import EntityFileRepository
from repository.relation_dict_repository import RelationDictRepository
from repository.relation_file_repository import RelationFileRepository


class TestEntityDictRepository(unittest.TestCase):
    def setUp(self):
        self.repo = EntityDictRepository()

    def test_add_entity(self):
        self.repo.add_entity(Student(None, None))
        entity, = self.repo.get_entity(Entity(None))
        self.assertEqual(entity["ID"], "1")

    def test_del_entity(self):
        self.repo.add_entity(Student(None, None))
        self.repo.del_entity(Entity("1"))
        entities = self.repo.get_entity(Entity(None))
        self.assertEqual(len(entities), 0)
        with self.assertRaises(LookupError):
            self.repo.del_entity(Entity("1"))

    def test_mod_entity(self):
        self.repo.add_entity(Student(None, "old"))
        self.repo.mod_entity(Student("1", "new"))
        entity, = self.repo.get_entity(Entity(None))
        self.assertEqual(entity["NAME"], "new")
        with self.assertRaises(LookupError):
            self.repo.mod_entity(Student("2", "error"))


class TestEntityFileRepository(TestEntityDictRepository):
    def setUp(self):
        self.file = open("test_repo.txt", "w")
        self.file.close()
        self.repo = EntityFileRepository(self.file.name, Student)

    def tearDown(self):
        os.remove(self.file.name)


class TestRelationDictRepository(unittest.TestCase):
    def setUp(self):
        self.repo_left = EntityDictRepository()
        self.repo_right = EntityDictRepository()
        self.repo = RelationDictRepository(self.repo_left, self.repo_right)
        self.repo_left.add_entity(Entity(None))
        self.repo_left.add_entity(Entity(None))
        self.repo_right.add_entity(Entity(None))
        self.repo_right.add_entity(Entity(None))

    def test_add_entity(self):
        self.repo.add_entity(Relation(None, "1", "2"))
        entity, = self.repo.get_entity(Entity(None))
        self.assertEqual(entity["ID"], "1")
        self.assertEqual(entity["LEFT ID"], "1")
        self.assertEqual(entity["RIGHT ID"], "2")
        with self.assertRaises(PermissionError):
            self.repo.add_entity(Relation(None, "1", "3"))
        with self.assertRaises(PermissionError):
            self.repo_left.del_entity(Entity("1"))
        with self.assertRaises(PermissionError):
            self.repo_right.del_entity(Entity("2"))

    def test_del_entity(self):
        self.repo.add_entity(Relation(None, "1", "2"))
        self.repo.del_entity(Entity("1"))
        entities = self.repo.get_entity(Entity(None))
        self.assertEqual(len(entities), 0)

    def test_mod_entity(self):
        self.repo.add_entity(Relation(None, "1", "2"))
        self.repo.mod_entity(Relation("1", "2", "1"))
        entity, = self.repo.get_entity(Entity(None))
        self.assertEqual(entity["LEFT ID"], "2")
        self.assertEqual(entity["RIGHT ID"], "1")
        with self.assertRaises(PermissionError):
            self.repo.mod_entity(Relation("1", "1", "3"))
        with self.assertRaises(LookupError):
            self.repo.mod_entity(Relation("2", "1", "1"))


class TestRelationFileRepository(TestRelationDictRepository):
    def setUp(self):
        self.file = open("test_repo.txt", "w")
        self.file_left = open("test_repo_left.txt", "w")
        self.file_right = open("test_repo_right.txt", "w")
        self.file.close()
        self.file_left.close()
        self.file_right.close()
        self.repo_left = EntityFileRepository(self.file_left.name, Entity)
        self.repo_right = EntityFileRepository(self.file_right.name, Entity)
        self.repo = RelationFileRepository(self.repo_left, self.repo_right, self.file.name, Relation)
        self.repo_left.add_entity(Entity(None))
        self.repo_left.add_entity(Entity(None))
        self.repo_right.add_entity(Entity(None))
        self.repo_right.add_entity(Entity(None))

    def tearDown(self):
        os.remove(self.file.name)
        os.remove(self.file_left.name)
        os.remove(self.file_right.name)
