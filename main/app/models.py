from django.db import models

class Item_s(models.Model):
    place = models.CharField(max_length=3)
    name = models.CharField(max_length=255)
