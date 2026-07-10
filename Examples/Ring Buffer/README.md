# 🔄 Ring Buffer (Circular Buffer)
> A clean C implementation of a Ring Buffer — one of the most fundamental data structures in embedded systems programming.

---

## 📖 What is a Ring Buffer?

A **Ring Buffer** (also called a **Circular Buffer** or **Circular Queue**) is a fixed-size data structure that uses a single, contiguous block of memory as if it were connected end-to-end in a circle.

Instead of shifting data around when items are added or removed (like a regular array), it simply moves two pointers — a **Head** and a **Tail** — around the buffer. When a pointer reaches the end of the array, it **wraps back to the start**, hence the "circular" or "ring" behaviour.

```
  Index:  0    1    2    3    4    5    6    7    8    9
        ┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
Buffer: │ 10 │ 20 │ 30 │ 40 │ 50 │ 60 │ 70 │ 80 │ 90 │100 │
        └────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
          ▲                                               ▲
        Tail                                           Head
        (read                                         (write
        here)                                          here)
```

When `Head` reaches index 9 and needs to advance, it wraps around to index 0 — **no data is moved, only the pointer changes.**

---

## 🧠 The Core Concept: Two Pointers + A Counter

This implementation tracks three things:

| Variable      | Role                                             |
|---------------|--------------------------------------------------|
| `Head`        | Points to the **next empty slot** to write into  |
| `Tail`        | Points to the **oldest item** to read from       |
| `count`       | Tracks how many items are currently in the buffer|

### The Wrap-Around Formula
The secret to the circular behaviour is the **modulo operator**:
```c
Head = (Head + 1) % Buffer_Size;
Tail = (Tail + 1) % Buffer_Size;
```
When `Head` or `Tail` reaches `Buffer_Size`, the `%` operation resets it back to `0` — seamlessly wrapping around without any branching or memory movement.

---

## ⚙️ How the Operations Work

### Writing (Enqueue) — `API_WriteToBuffer()`
```
1. Is the buffer FULL? (count == Buffer_Size)
   ├── YES → Drop the data, print a warning. Do nothing.
   └── NO  → Write data at Buffer[Head]
              Move Head forward: Head = (Head + 1) % Buffer_Size
              Increment count
```

### Reading (Dequeue) — `API_ReadfromBuffer()`
```
1. Is the buffer EMPTY? (count == 0)
   ├── YES → Print a warning. Do nothing.
   └── NO  → Read data from Buffer[Tail]
              Move Tail forward: Tail = (Tail + 1) % Buffer_Size
              Decrement count
```

### The FIFO Guarantee
Because `Tail` always chases `Head`, the **first item written is always the first item read** — this is a classic **FIFO (First In, First Out)** queue.

---

## 📁 Project Structure

```
Ring Buffer/
├── ring_buffer.h      # Public API — function prototypes & extern declarations
├── ring_buffer.c      # Implementation — buffer logic lives here
├── main.c             # Visual test/demo — exercises all scenarios
└── README.md          # You are here
```

### `ring_buffer.h` — The Public Interface
Exposes the state variables via `extern` (so `main.c` can read them for the visualizer) and declares the four API functions.

### `ring_buffer.c` — The Implementation
Defines the actual buffer array and all four functions. The buffer size is set here:
```c
int Buffer_Size = 10;
int Buffer[10];
```

### `main.c` — The Visual Demo
Runs six test scenarios to prove every behaviour works:
1. **Fill** the buffer completely
2. **Overfill** — attempt to write when full (data dropped)
3. **Read** 3 items back out
4. **Write again** — watch `Head` wrap around
5. **Drain** the remaining items
6. **Read from empty** — triggers the underflow guard

---

## 🚀 Build & Run

### Prerequisites
You need GCC. This project was tested with **GCC 16.1.0** from [MSYS2](https://www.msys2.org/).

### Compile
```powershell
# In PowerShell — set up the MSYS2 runtime first
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH

# Compile both source files
gcc main.c ring_buffer.c -o ring_buffer_test.exe
```

### Run
```powershell
.\ring_buffer_test.exe
```

### Expected Output
```
=== CIRCULAR BUFFER VISUALIZER ===
Buffer Size: 10

--- 1. FILLING THE BUFFER ---
Writing: 10
  [Head: 1 | Tail: 0 | Count: 1]
...
Writing: 100
  [Head: 0 | Tail: 0 | Count: 10]   <- Head wrapped back to 0!

--- 2. TRYING TO OVERFILL ---
Writing: 999
Buffer is Full! Dropping data.  [Head: 0 | Tail: 0 | Count: 10]

--- 3. READING 3 ITEMS ---
Read out: 10
  [Head: 0 | Tail: 1 | Count: 9]    <- Tail advances on reads
...

--- 6. TRYING TO READ FROM EMPTY ---
Buffer is Empty
```

---

## 💡 Why Use a Ring Buffer?

Ring Buffers are everywhere in embedded systems because they solve a critical real-world problem: **producers and consumers that run at different speeds.**

| Use Case | Producer | Consumer |
|---|---|---|
| **UART / Serial comms** | Interrupt (fast) | Main loop (slow) |
| **Audio streaming** | DMA transfer | Codec playback |
| **Sensor data logging** | ADC sampling | SD card write |
| **OS task queues** | Multiple tasks | Scheduler |
| **Network packet buffers** | NIC hardware | TCP/IP stack |

### Key Advantages
- ✅ **O(1)** read and write — always constant time, regardless of buffer size
- ✅ **Zero memory allocation** — fixed size, known at compile time (critical for embedded)
- ✅ **No shifting** — data stays in place, only pointers move
- ✅ **Thread-safe friendly** — with a single producer and single consumer, it is naturally lock-free
- ✅ **Predictable memory footprint** — no heap fragmentation

---

## ⚠️ Limitations of This Implementation

| Limitation | Detail |
|---|---|
| **Fixed size** | `Buffer_Size` is set at compile time. No dynamic resizing. |
| **Not thread-safe** | `count` is read and written in multiple places. In a multi-threaded or ISR context, access must be protected with a mutex or critical section. |
| **Integer data only** | The buffer stores `int`. A production implementation would use `uint8_t` or a generic `void*` element type. |
| **Global state** | Variables like `Head`, `Tail`, and `count` are global. A struct-based approach would allow multiple independent buffer instances. |

---

## 🔬 Concept Deep Dive: Full vs. Empty Disambiguation

A classic challenge with ring buffers is: **how do you tell the difference between a full buffer and an empty one?**

When the buffer is empty: `Head == Tail`
When the buffer is full after wrapping: `Head == Tail`

Both states look the same if you only track the two pointers! There are three standard solutions:

| Strategy | How it works | Used here? |
|---|---|---|
| **Count variable** | Track `count` separately. Full = `count == Size`, Empty = `count == 0` | ✅ Yes |
| **Waste one slot** | Buffer is "full" when `(Head + 1) % Size == Tail`. Simple but wastes 1 slot. | ❌ No |
| **Mirrored indices** | Use indices of size `2 * Buffer_Size`. Elegant but complex. | ❌ No |

This implementation uses the **count variable** approach — the most readable and beginner-friendly strategy.

---

## 📚 Further Reading
- 🎥 [Ring Buffer / Circular Buffer — Video Tutorial](https://youtu.be/uvD9_Wdtjtw?si=5v1sDFHfCvYCQ9e1) ← **Start here!**
- [Wikipedia — Circular Buffer](https://en.wikipedia.org/wiki/Circular_buffer)
- *Making Embedded Systems* by Elecia White — Chapter on queues and buffers
- *The Art of Designing Embedded Systems* by Jack Ganssle

---

## 🌳 Part of the Embedded Systems SkillTree

This example is part of a structured learning path for embedded systems engineers.

> 📂 **[colonelblacc/Embedded-Systems-SkillTree](https://github.com/colonelblacc/Embedded-Systems-SkillTree)**

The SkillTree repo contains hands-on C examples organised by topic — each one designed to teach a core embedded concept through working, well-commented code.
