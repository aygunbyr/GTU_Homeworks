from django.db import models

class Product(models.Model):
    name = models.CharField(max_length=120, verbose_name='Product Name')
    description = models.CharField(max_length=250, verbose_name='Description')
    price = models.IntegerField(default=0, verbose_name='Price')
    discount_rate = models.IntegerField(default=0, verbose_name='Discount Rate %')
    on_sale = models.BooleanField(default=True, verbose_name='On Sale') # True = active product

    def __str__(self):
        return 'Product'