# Smart Story Genre Classifier 📚🤖

An automated text classification system implemented in C++ designed to analyze literary stories and accurately determine their underlying genre. The project utilizes weighted keyword matching across pre-defined genre dictionaries to extract insights, rank dominant elements, and compute statistical confidence levels for each prediction. 

This project was developed as the secondary computer programming assignment during my first semester at the University of Tehran. (Winter 2023)

## 📝 Project Context: "The Foolish Writer"
The system resolves a humorous academic scenario where an publishing agency employs a writer who can produce stories but lacks the ability to identify their genres. This pipeline automates the manual oversight previously done by course TAs by implementing a deterministic natural language processing (NLP) scoring matrix.

---

## 🌟 Key Features

- **Multi-Genre Evaluation Matrix:** Evaluates text streams against four primary genres: *Fantasy, Mystery, Romance,* and *Sci-Fi*.
- **Weighted Frequency Scoring:** Rather than counting simple occurrences, the algorithm maps words to specified weights extracted dynamically from datasets (e.g., `SciFi.csv`).
- **Statistical Confidence Output:** Calculates the precision and mathematical confidence interval for each genre dynamically based on the total distribution of matched terms.
- **Top Keyword Extractor:** Isolates and ranks the top 5 most influential keywords causing the factual classification within the prose.
- **Dynamic File Processing & Logging:** Automates text tokenization, strips parsing artifacts, handles string-to-integer streams (`stringstream`), and pipes data directly into structured summaries.

---

## 📂 Code Architecture & Data Structures

The system relies on strong modularization through vectorized structures rather than static arrays, minimizing memory overhead and accommodating unconstrained text lengths:

* **`struct MyStructure`**: Handles vocabulary indexing, storing targeted semantic keywords alongside their specific integer weights parsed from comma-separated tables (`.csv`).
* **`struct analiz`**: The central operational matrix tracking individual metrics including text scoring arrays, confidence percentages per genre, and metadata logs.
* **`processFile()`**: Parses and builds the dynamic dictionary maps for each genre layout while dropping headers and parsing tokens safely.
* **`findMaxValuesAndIndices()`**: A specialized sorting sub-routine tracking tracking bounds to secure the top five scoring words without modifying structural integrity.

---

## 📊 Evaluation Metrics & Formulas

The core decision engine determines the absolute genre by locating the highest calculated weight factor:

$$\text{Confidence Score}_{\text{Genre}} = \frac{\text{Matched Weights Within Genre}}{\text{Total Matched Weights Across All Genres}} \times 100$$

The output renders a thorough dataset mapping out precise frequency logs, specific keyword hits, confidence levels, and the ultimate definitive classification.

---

## 🛠️ Compilation & Execution

The project requires a standard C++ compiler supporting C++11 or higher (due to `std::vector` usage and standard conversions).

1. **Verify Asset Directory:** Ensure all dataset matrices (`Fantasy.csv`, `Mystery.csv`, `Romance.csv`, `SciFi.csv`) and text files (e.g., `Cosmic_Convergence.txt`) reside in the working execution directory.

2. **Compile via GCC (g++):**
   ```bash
   g++ -std=c++11 Source.cpp -o genre_classifier
