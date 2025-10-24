# ft_ssl

> Usage : ./ft_ssl **command** [-pqr] [-s`<string>`] [file]

Supported commands are :
- **md5**
- **sha256**

## Documentation

### SSL

The binary`./ft_ssl` parses it's CLI and delivers a linked list of inputs to be processed through the **command** to produce an output called **digest**.\
This linked list can be comprised of `string input`, `infiles`, or simply `standard input from terminal`. Each input will be **handled independently** from the others. Multiple inputs of **different types** can be used **sequentially**.

Once all the inputs were processed, all their digest will be printed according to their respective options. (Each input's digest inherits from the previous' options and can add it's own without affecting previous digests.)

### MD5

The [md5 algorithm wikipedia page](https://en.wikipedia.org/wiki/MD5).

[Collision wikipedia page](https://en.wikipedia.org/wiki/Hash_collision).\
[Collision example](https://crypto.stackexchange.com/questions/1434/are-there-two-known-strings-which-have-the-same-md5-hash-value).

An okay-ish step by step explanation of the [md5 algorithm](https://www.comparitech.com/blog/information-security/md5-algorithm-with-examples/).\
**WARNING :** most of the values used in this example are wrong, favor using the [official md5 documentation rfc](https://www.ietf.org/rfc/rfc1321.txt) for those.

And a good [md5 block visualization](https://fthb321.github.io/MD5-Hash/MD5OurVersion2.html).

<details>

<summary> The full md5 algorithm explanation. </summary>

The MD5 Algorithm takes an input of **any length** and turns it into a digest of **32 bytes**. For a given input, the digest will always be the same.\
To achieve this, the input is split into blocks of 512 bits (64 bytes) and processed one at a time.

The block separation works like so : \
// TODO: Insert md5 block visualization \

After initializing the first block, a **context** will be set to **constant values** defined in the [md5 rfc](https://www.ietf.org/rfc/rfc1321.txt), these values are named A, B, C and D. (The algorithm uses other constant values specified in the [rfc](https://www.ietf.org/rfc/rfc1321.txt), most are defined [here](./srcs/md5/md5_constants.c))\
This context will be altered during what is called a **step**, each block will go through one step each, **inhreriting the previous step context** instead of the initial **constant values**.

<mark>**EACH BLOCK HAS TO BE PROCESSED IN  LITTLE ENDIAN**</mark>
> I have to admit this part was the hardest to understand. I don't know if it is a quirk of my implementation but i had to convert each block to little-endian before processing it and back to big-endian after. If you need a refresher on this concept, go to the bottom of this README.

#### Step, rounds and operations
A **step**, as shown in the image below, takes the 512-bit **message block** and mixes it **4 rounds** of **16 operations** each.

#### [Figure 1]
A visual representation of the core MD5 loop. [Source](https://cdn.comparitech.com/wp-content/uploads/2021/06/md5-no-2fix-02-scaled.jpg)\
<img src="./Documentation/md5_main_loop.jpeg" alt="md5 algorithm core MD5 loop" width="640" height="1280" />

Each **round** will input a 1/16th of the block in each of the **operation**'s iteration. \
Depending on the **round** number (1-4), the **operation** will behave differently :
- **Bitwise Functions** F, G, H and I will be called for rounds 1, 2, 3 and 4 respectively.
- The **input order** for each 1/16th of the message, defined here in the [md5_constants.c](./srcs/md5/md5_constants.c) file, under the name`md5_input_order_array[4][16]`.
- A different **K value** from the `md5_k_constant[4][16]`.
- And finally a different **bitwise left shift** from `md5_shift_array[4][16]`.

Then we add **context vector B** to **context vector A**.
The last step of the **operation** is to **shuffle** each **context vector** to the **right** (A to B, B to C, C to D and D to A).

#### [Figure 2]
A visual representation of the individual operation inside the core MD5 loop. [source](https://cdn.comparitech.com/wp-content/uploads/2021/06/md5-011-scaled.jpg)\
<img src="./Documentation/md5_main_function.jpeg" alt="md5 algorithm individual operation" width="672" height="640" />

With this operation done we can do the **63 remaining operations**. \
If there is more of the input to process, we **fetch a new block** and go back to the **beginning** of the rounds, this time with the **context vectors from the previous block**.

Finally once all the blocks have been processed, we **convert** the 4 context vectors to the **digest** and return that to the **SSL program** to output later.

</details>

### Endianness

#### [Figure 3]
In case you need a reminder about [endianness](https://en.wikipedia.org/wiki/Endianness), here is a visual explanation of how it works :\
<img src="./Documentation/endianness.png" alt="Visual representation of endianness" width="750" height="750" />
