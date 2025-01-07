from hashlib import sha1
import random

N = 1_000_000
t = 500
r = 20
alpha = r / (1+r)
m_0 = (2*r*N) / (t+2)
m_t = (2*alpha*N) / (t+2)

n_tables = 4

def hash(data: int) -> str:
    return sha1(str(data).encode()).hexdigest()

def reduction(h: str, c: int, tid: int) -> int:
    global t, n_tables, N
    if 0 <= c <= t and 0 <= tid < n_tables:
        return (int(h,16)+c+tid*t) % N
    else:
        raise ValueError("Invalid c or tid")

def hash_reduction(data: int, c: int, tid: int) -> int:
    return reduction(hash(data), c, tid)

def import_table(filename: str) -> list[tuple[int, ...]]:
    with open(filename, 'r') as f:
        return [tuple(map(int, line.split())) for line in f]

def attack_chain(c: int, tid: int, h: str) -> int:
    global t
    x = reduction(h, c, tid)
    while c < t-1:
        c += 1
        x = hash_reduction(x, c, tid)
    return x

def match(endp: int, table: list[tuple[int,...]]) -> tuple[int,...]:
    for elem in table:
        if elem[1] == endp:
            return elem
    raise ValueError("Match not found")

def rebuild(elem: tuple[int,...], tid: int, c: int) -> int:
    x = elem[0]
    for new_c in range(c):
        x = hash_reduction(x, new_c, tid)
    return x

def check(cand: int, h: str) -> bool:
    return hash(cand) == h

def main():
    print("Choosing random number to hash")
    number = random.randint(0, 1_000_000)
    h = hash(number)
    print(f"Number: {number}, Hash: {h}")
    # TODO

def test_hash():
    assert hash(123456) == '7c4a8d09ca3762af61e59520943dc26494f8941b'
    assert hash(123) == '40bd001563085fc35165329ea1ff5c5ecbdbbeef'

def test_reduction():
    assert reduction('7c4a8d09ca3762af61e59520943dc26494f8941b', 1, 0) == 33820
    assert reduction('40bd001563085fc35165329ea1ff5c5ecbdbbeef', 1, 0) == 137520

def test_hash_reduction():
    assert hash_reduction(123456, 1, 0) == 33820
    assert hash_reduction(123, 1, 0) == 137520

def test_import_table():
    assert import_table('testTable')[0] == (106334, 451)

def test_attack_chain():
    assert attack_chain(400, 0, 'c71767d2e29adcdb2fc6a245ad2e42f349bd7cc0') == 533389

def test_match():
    assert match(127810, import_table('testTable')) == (101973,127810)

def test_rebuild():
    assert rebuild((123456,533389), 0, 400) == 249467

def test_check():
    assert check(123456, '7c4a8d09ca3762af61e59520943dc26494f8941b') == True
