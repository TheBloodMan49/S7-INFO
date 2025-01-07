import typing
import click
from Crypto.Util.number import getPrime
import json

Key = typing.Tuple[int, int]

def gen_key(len: int) -> tuple[Key, Key]:
    p = getPrime(len)
    q = getPrime(len)
    n = p * q
    phi = (p - 1) * (q - 1)
    e = 2**16 + 1
    d = pow(e, -1, phi) # Yes this computes the modular inverse
    return (n, e), (n, d)

def exp(m: int, key: Key) -> int:
    n, e = key
    return pow(m, e, n)

def code(m: str) -> int:
    return int("".join([str(ord(c)-ord('a')+10) for c in m])) # Map a-z to 10-35

def decode(c: int) -> str:
    res = ""
    c = str(c)
    for i in range(0, len(c), 2):
        res += chr(int(c[i:i+2]) + ord('a') - 10)
    return res

def RSAenc(cleartext: str, pubkey: Key) -> int:
    return exp(code(cleartext), pubkey)

def RSAdec(ciphertext: int, privkey: Key) -> str:
    return decode(exp(ciphertext, privkey))

# Helpers to store and load keys
def store_key(filename: str, key: Key):
    with open(filename, 'w') as f:
        json.dump(key, f)

def load_key(filename: str) -> Key:
    with open(filename, 'r') as f:
        return tuple(json.load(f))

# Cli interface
@click.group()
def cli():
    pass

@cli.command()
@click.argument('keylen', type=int)
@click.option('-s', '--store', type=str, help='Store the generated key in a file')
def genkey(keylen, store):
    pubkey, privkey = gen_key(keylen)
    if store:
        store_key(f"{store}_pub.json", pubkey)
        store_key(f"{store}_priv.json", privkey)
        click.echo(f"Keys stored in {store}_pub.json and {store}_priv.json")
    else:
        click.echo(f"Public key: {pubkey}")
        click.echo(f"Private key: {privkey}")

@cli.command()
@click.argument('cleartext')
@click.argument('pubkey', required=False)
@click.option('-s', '--store', type=str, help='Retrieve the public key from a file')
def enc(cleartext, pubkey, store):
    if store:
        pubkey = load_key(store)
    elif pubkey:
        pubkey = tuple(map(int, pubkey.split(",")))
    else:
        raise click.UsageError("Either PUBKEY or --store option must be provided.")
    click.echo(RSAenc(cleartext.lower(), pubkey))

@cli.command()
@click.argument('ciphertext', type=int)
@click.argument('privkey', required=False)
@click.option('-s', '--store', type=str, help='Retrieve the private key from a file')
def dec(ciphertext, privkey, store):
    if store:
        privkey = load_key(store)
    elif privkey:
        privkey = tuple(map(int, privkey.split(",")))
    else:
        raise click.UsageError("Either PRIVKEY or --store option must be provided.")
    click.echo(RSAdec(ciphertext, privkey))

if __name__ == '__main__':
    cli()