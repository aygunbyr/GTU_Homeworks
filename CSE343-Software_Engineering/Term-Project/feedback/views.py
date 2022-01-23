from django.shortcuts import render, HttpResponse
from .forms import FeedbackForm

def feedback_index(request):
    form=FeedbackForm(request.POST or None,request.FILES or None)
    if form.is_valid():
        form.save()
    else:
        form=FeedbackForm()
    context = {
        'form': form,
    }
    return render(request, 'feedback/form.html', context)


