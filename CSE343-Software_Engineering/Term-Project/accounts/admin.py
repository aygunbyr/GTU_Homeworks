from django.contrib import admin
from .models import Profile

class ProfileAdmin(admin.ModelAdmin):
    class Meta:
        model = Profile

    list_display = ['user', 'bio', 'location', 'birth_date', 'avatar_image']
    list_filter = ['birth_date']

admin.site.register(Profile, ProfileAdmin)
