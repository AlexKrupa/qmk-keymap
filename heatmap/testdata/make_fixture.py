import json
import os
import sqlite3
import sys

FIXTURE_PATH = os.path.join(os.path.dirname(__file__), "keymapp.sqlite3")

SCHEMA = """
create table heatmap (
    revisionId TEXT NOT NULL UNIQUE,
    enabled boolean DEFAULT 0,
    data BLOB DEFAULT NULL
);
create table revision (
    revisionId TEXT NOT NULL UNIQUE,
    data BLOB DEFAULT NULL
);
"""


def build(source_path, fixture_path):
    source = sqlite3.connect(f"file:{source_path}?mode=ro", uri=True)
    heatmaps = source.execute("select revisionId, enabled, data from heatmap").fetchall()
    revisions = source.execute("select revisionId, data from revision").fetchall()
    source.close()

    if os.path.exists(fixture_path):
        os.remove(fixture_path)

    fixture = sqlite3.connect(fixture_path)
    fixture.executescript(SCHEMA)
    fixture.executemany("insert into heatmap values (?, ?, ?)", heatmaps)
    for revision_id, data in revisions:
        # A real revision blob is a full layout dump - only these fields are read.
        revision = json.loads(data)["layout"]["revision"]
        layers = [
            {
                "title": layer.get("title"),
                "keys": [{"tap": {"code": (key.get("tap") or {}).get("code")}}
                         for key in layer["keys"]],
            }
            for layer in revision["layers"]
        ]
        minimal = {"layout": {"revision": {
            "createdAt": revision.get("createdAt"),
            "layers": layers,
        }}}
        fixture.execute(
            "insert into revision values (?, ?)",
            (revision_id, json.dumps(minimal)),
        )
    fixture.commit()
    fixture.close()


if __name__ == "__main__":
    build(sys.argv[1], FIXTURE_PATH)
