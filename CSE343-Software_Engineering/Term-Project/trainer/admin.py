from django.contrib import admin
from .models import Trainer, Reservation, CalendarEvent

admin.site.register(Trainer)
admin.site.register(Reservation)
admin.site.register(CalendarEvent)