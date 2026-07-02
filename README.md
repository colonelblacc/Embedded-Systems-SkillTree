# Interactive Embedded Systems Skill Tree

An interactive, responsive, and real-time synchronized skill tree tracker for Embedded Systems engineers. Based on visual hex grid skill templates, this tracker allows users to mark their skills, track overall progress, sync state across devices using Firebase, and share their completed skill profiles with others.

Live Demo: [colonelblacc.github.io/Embedded-Systems-SkillTree](https://colonelblacc.github.io/Embedded-Systems-SkillTree)

---

## 🚀 Key Features

*   **Interactive Visual Hex Grid**: Responsive, vector-based interactive SVG hexagon skills matrix.
*   **Dynamic Lucide Icons**: Automatically maps skills to standard Lucide icons based on text-proximity algorithms.
*   **Real-time Firebase Synchronization**: Real-time progress synchronization with Firestore triggered by manual username lookup/creation.
*   **Offline Fallback**: Automatically falls back to browser LocalStorage when Firebase is unavailable or when operating in offline mode.
*   **Shareable Progress Profiles**: Generate unique profile links (e.g. `?user=USERNAME`) to share your tree with others.
*   **Embedded Quote Banner**: A bold black banner at the bottom of the skill tree displaying rotating motivational quotes.

---

## 🛠️ Getting Started & Local Development

### 1. Build System Setup
The project uses a Python script (`build.py`) to merge the interactive visual SVG with the HTML layout template. Do **not** edit `index.html` directly, as it will be overwritten.

To make adjustments:
1. Edit logic or styles in `index.template.html`.
2. Edit SVG nodes, layouts, or texts in `MakerSkillTree - embedded_systems.svg`.
3. Run the compiler:
    ```bash
    python build.py
    ```

### 2. Running Locally
Start a local server to test features (e.g. LocalStorage, browser-level routing):
```bash
# Using Python
python -m http.server 8000
```
Open your browser and navigate to `http://localhost:8000`.

---

## ⚙️ Firebase Firestore Configuration

The project is pre-configured with a real-time Firestore database schema:
*   **Collection**: `skilltrees`
*   **Document ID**: Normalised username (`USERNAME_UPPERCASE_WITH_UNDERSCORES`).
*   **Structure**:
    ```json
    {
      "username": "testuser",
      "progress": {
        "hex_id_1": true,
        "hex_id_2": false
      }
    }
    ```

If you wish to host your own version:
1. Create a Firebase project and set up **Firestore Database** and **Anonymous Authentication**.
2. Replace `firebaseConfig` credentials inside `<script type="module">` in `index.template.html`.
3. Re-run `python build.py`.

---

## 🧑‍💻 Contribution Guidelines (For Maintainers)

If you are receiving pull requests or hosting this repository, keep the following guidelines in mind:

### 1. The Template-First Rule
*   **CRITICAL**: All HTML, CSS, and JS edits must be made inside [index.template.html](index.template.html).
*   Any PR that directly modifies [index.html](index.html) should be rejected and requested to rebuild via [build.py](build.py).

### 2. Modifying Skill Hexagons
*   To add, remove, or change the text of hexagons, modify [MakerSkillTree - embedded_systems.svg](MakerSkillTree%20-%20embedded_systems.svg) directly using a vector editor (like Illustrator, Inkscape) or manual XML editing.
*   Ensure every new hexagon path has the class `cls-12` and a unique `id` attribute.

### 3. Icon Proximity Matching
*   Icons are injected dynamically on page load via `renderHexagonIcons()`.
*   The script calculates the centroid of each `.cls-12` hexagon path and finds the nearest `.textbox-inner` text node.
*   If you add a new hexagon text that does not show a proper icon, add a mapping keyword to the `skillIconMap` dictionary in `index.template.html`.
*   Ensure keywords in `skillIconMap` are sorted by length inside the code to prevent partial-word overlaps (e.g. `ble` matching `troubleshoot`).

### 4. Code Standards
*   Keep comments standard using `//` for Javascript. Avoid Python-style `#` comment structures inside template scripts to prevent build-level parsing errors.
*   Ensure all SVG element color overrides are specified using `!important` to override embedded SVG attributes.

---

## 📜 Credits & License

*   **Original Concept & Design**: Based on the [MakerSkillTree](https://github.com/sjpiper145/MakerSkillTree) by [sjpiper145](https://github.com/sjpiper145).
*   **License**: Licensed under [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)](https://creativecommons.org/licenses/by-nc-sa/4.0/).

