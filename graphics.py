import argparse
import os
import sys

import matplotlib.pyplot as plt
import pandas as pd


def load_table(folder):
    path = os.path.join(folder, "avg.csv")
    if not os.path.isfile(path):
        sys.exit(f"Файл не найден: {path}")

    table = pd.read_csv(path, skipinitialspace=True)
    table.columns = [c.strip() for c in table.columns]

    needed = {"n", "after_ns", "before_ns"}
    missing = needed - set(table.columns)
    if missing:
        sys.exit(f"В {path} нет столбцов: {', '.join(sorted(missing))}. "
                 f"Найдены: {', '.join(table.columns)}")

    return table.sort_values("n")


def plot_single(table, column, label, color, marker, filename):
    fig, ax = plt.subplots(figsize=(7, 4.5))
    ax.plot(table["n"], table[column], marker=marker, color=color, label=label)
    ax.set_xlabel("Размер списка n")
    ax.set_ylabel("Время одной вставки, нс")
    ax.set_ylim(bottom=0)
    ax.grid(True)
    ax.legend()
    fig.tight_layout()
    fig.savefig(filename, dpi=200)
    return fig


def plot_both(table, filename):
    fig, ax = plt.subplots(figsize=(7, 4.5))
    ax.plot(table["n"], table["after_ns"], marker="o", color="tab:blue",
            label="insertAfter")
    ax.plot(table["n"], table["before_ns"], marker="s", color="tab:red",
            label="insertBefore")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.set_xlabel("Размер списка n")
    ax.set_ylabel("Время одной вставки, нс")
    ax.grid(True, which="both")
    ax.legend()
    fig.tight_layout()
    fig.savefig(filename, dpi=200)
    return fig


def main():
    parser = argparse.ArgumentParser(description="Графики по avg.csv")
    parser.add_argument("folder", nargs="?", help="папка с avg.csv (например, best или worse)")
    parser.add_argument("--show", action="store_true", help="показать графики на экране")
    args = parser.parse_args()

    folder = args.folder or input("Папка с avg.csv (best / worse): ").strip()
    table = load_table(folder)

    out = lambda name: os.path.join(folder, name)
    plot_single(table, "after_ns", "insertAfter", "tab:blue", "o", out("graph_after.png"))
    plot_single(table, "before_ns", "insertBefore", "tab:red", "s", out("graph_before.png"))
    plot_both(table, out("graph_both.png"))

    print(f"Готово. Графики сохранены в папку {folder}:")
    print("  graph_after.png, graph_before.png, graph_both.png")

    if args.show:
        plt.show()


if __name__ == "__main__":
    main()
