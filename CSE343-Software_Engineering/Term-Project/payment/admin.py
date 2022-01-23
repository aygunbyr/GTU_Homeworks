from django.contrib import admin
from payment.models import Sale

class SaleAdmin(admin.ModelAdmin): 
    list_display = [f.name for f in Sale._meta.fields]
admin.site.register(Sale, SaleAdmin)