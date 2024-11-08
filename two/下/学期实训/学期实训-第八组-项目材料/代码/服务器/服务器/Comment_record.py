# from datetime import datetime
import time


class Node(object):
    next = None
    date = 0

    def __init__(self):
        self.next = None
        self.date: float = 0


class CommentRecord:
    count = 0
    list_len = 3
    root = None
    new = None
    last = None

    def __init__(self):
        # max = 5
        self.count = 0
        self.list_len = 3
        self.root = Node()
        self.root.next = Node()
        self.root.next.next = Node()
        self.root.next.next.next = self.root
        self.new = self.root.next.next
        self.last = self.root

    # 259200(三天)只能发3条
    def commentable(self):
        if self.count > 5:
            return False
        # if time.time() - self.last.date < 259200:
        if time.time() - self.last.date < 60:
            return False

        return True

    def add(self):
        self.count += 1
        if not self.commentable():
            return False
        self.last = self.last.next
        self.new = self.new.next
        self.new.date = time.time()
        return True
