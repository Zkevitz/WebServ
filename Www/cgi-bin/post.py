#!/usr/bin/env python3
# coding=utf-8
import os
import sys

# Lire le contenu POST
# for key, value in os.environ.items():
#     print(f"{key}: {value}")
#     print("\n")
# sys.exit(0)

content_length = int(os.environ.get("CONTENT_LENGTH", 0))
if content_length <= 6:
    post_data = "AUCUN CONTENU POST"
else :
    post_data = sys.stdin.read(content_length)

# Répondre
print(f"<html><body><h1>Reçu via POST :</h1><p>{post_data}</p></body></html>")
