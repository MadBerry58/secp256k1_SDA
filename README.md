# secp256k1_SDA
Smooth Distribution Attacker

Elliptic Curve Cryptography (ECC), is a lightweight asymmetric key protocol, ofering equivalent security to that of RSA, but with much smaller key sizes.

One of the most popular uses for ECC is in cryptocurrency, where the public keys are used as wallets, allowing for fast and secure transaction signing.
Unfortunatelly, unlike RSA, this type of attack is more vulnerable to bruteforce attacks.
This is because the search space, although vast, can be searched through by multiple processes, without having the connection between them as a speed bottleneck.

This program aims to demonstrate this kind of attack for the secp256k1_SDA elliptic curve, allowing the user to choose between different worker configuration and attack algorithms.

A simple architecture document can be found inside the documentation folder

Explanation:

Since the security of the ECC algorithms is ensured by the discreete logarithm problem, and the private key is hidden behind the point arithmetic, the only way to execute an attack is by trying to guess the right key.
Of course, just trying random keys would most likely take more than the age of the universe, so a more targeted approach is needed.
The first step is to create a database of known Point-Key pairs. The easiest way to do this is to calculate every point starting from the generator point (k = 1) up to the limit of the user's allocated RAM memory.

By knowing that any point Q is equivalent to a key k, and the point -Q has the equivalent key order-k (with order being the total number of valid points), while preserving its X coordinate, the size of the known points can be increased. This is done by retaining only the Key and the X coordinate, as deducing -K and -Y is trivial.

Another optimization can be done by exploiting the discreete logarithm problem. Since the discreete logarithm problem states that the members of a group don't have any distinguishing pattern to them, this effectively turns every point coordinate into a unique hash. As such, the low collision rate allows the truncation of the X coordinate, requiring storage space of at most 64 bits per key, out of the regular 256.

Using this principles, a central server with a high RAM memory can be used to generate, store and search through the known points database.
To facilitate this, a RB-Tree structure is used for searching the hashes, allowing the server to serve many clients at a time with little effort.

The actual search is done by the client nodes. This is done by incrementing the initial target point T with known values, saving the hashes and sending them to the server for checking.
To optimize this process, the increment added to the target is equivalent to the size of the used database, allowing for less overall steps.
To better distribute the work, the (-k = order - k) relationship is used again, by allowing the user to start the iteration from either the point T or -T.

To ensure the database against corruption by a malformed or mallicious client upload, a challange is issued for every upload request of the client.
This request consists of generating 3 random points from the client's claimed iterated space. The client must correctly specify the factors used to obtain the challange points. Once the uploaded, the server applies another challange to the message, searching for another 3 randomly generated points. As another layer of protection against attacks, the hash of the message must be specified during at the begining of the upload request.

Once the upload is verified, the server mark the iterated search space in the database.
